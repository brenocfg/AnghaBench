#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vpd_params {char* id; char* ec; char* sn; char* pn; char* na; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_VPD_UNIQUE_ID ; 
 unsigned int EC_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIND_VPD_KW (int,char*) ; 
 unsigned int ID_LEN ; 
 int /*<<< orphan*/  MACADDR_LEN ; 
 int PCI_VPD_INFO_FLD_HDR_SIZE ; 
 scalar_t__ PCI_VPD_LRDT_ID_STRING ; 
 int /*<<< orphan*/  PCI_VPD_LRDT_RO_DATA ; 
 int PCI_VPD_LRDT_TAG_SIZE ; 
 int /*<<< orphan*/  PN_LEN ; 
 int /*<<< orphan*/  SERNUM_LEN ; 
 int VPD_BASE ; 
 int VPD_BASE_OLD ; 
 unsigned int VPD_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,unsigned int) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 int pci_read_vpd (int /*<<< orphan*/ ,int,unsigned int,scalar_t__*) ; 
 int pci_vpd_find_tag (scalar_t__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int pci_vpd_info_field_size (scalar_t__*) ; 
 unsigned int pci_vpd_lrdt_size (scalar_t__*) ; 
 int /*<<< orphan*/  strim (char*) ; 
 int /*<<< orphan*/  vfree (scalar_t__*) ; 
 scalar_t__* vmalloc (unsigned int) ; 

int t4_get_raw_vpd_params(struct adapter *adapter, struct vpd_params *p)
{
	int i, ret = 0, addr;
	int ec, sn, pn, na;
	u8 *vpd, csum;
	unsigned int vpdr_len, kw_offset, id_len;

	vpd = vmalloc(VPD_LEN);
	if (!vpd)
		return -ENOMEM;

	/* Card information normally starts at VPD_BASE but early cards had
	 * it at 0.
	 */
	ret = pci_read_vpd(adapter->pdev, VPD_BASE, sizeof(u32), vpd);
	if (ret < 0)
		goto out;

	/* The VPD shall have a unique identifier specified by the PCI SIG.
	 * For chelsio adapters, the identifier is 0x82. The first byte of a VPD
	 * shall be CHELSIO_VPD_UNIQUE_ID (0x82). The VPD programming software
	 * is expected to automatically put this entry at the
	 * beginning of the VPD.
	 */
	addr = *vpd == CHELSIO_VPD_UNIQUE_ID ? VPD_BASE : VPD_BASE_OLD;

	ret = pci_read_vpd(adapter->pdev, addr, VPD_LEN, vpd);
	if (ret < 0)
		goto out;

	if (vpd[0] != PCI_VPD_LRDT_ID_STRING) {
		dev_err(adapter->pdev_dev, "missing VPD ID string\n");
		ret = -EINVAL;
		goto out;
	}

	id_len = pci_vpd_lrdt_size(vpd);
	if (id_len > ID_LEN)
		id_len = ID_LEN;

	i = pci_vpd_find_tag(vpd, 0, VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	if (i < 0) {
		dev_err(adapter->pdev_dev, "missing VPD-R section\n");
		ret = -EINVAL;
		goto out;
	}

	vpdr_len = pci_vpd_lrdt_size(&vpd[i]);
	kw_offset = i + PCI_VPD_LRDT_TAG_SIZE;
	if (vpdr_len + kw_offset > VPD_LEN) {
		dev_err(adapter->pdev_dev, "bad VPD-R length %u\n", vpdr_len);
		ret = -EINVAL;
		goto out;
	}

#define FIND_VPD_KW(var, name) do { \
	var = pci_vpd_find_info_keyword(vpd, kw_offset, vpdr_len, name); \
	if (var < 0) { \
		dev_err(adapter->pdev_dev, "missing VPD keyword " name "\n"); \
		ret = -EINVAL; \
		goto out; \
	} \
	var += PCI_VPD_INFO_FLD_HDR_SIZE; \
} while (0)

	FIND_VPD_KW(i, "RV");
	for (csum = 0; i >= 0; i--)
		csum += vpd[i];

	if (csum) {
		dev_err(adapter->pdev_dev,
			"corrupted VPD EEPROM, actual csum %u\n", csum);
		ret = -EINVAL;
		goto out;
	}

	FIND_VPD_KW(ec, "EC");
	FIND_VPD_KW(sn, "SN");
	FIND_VPD_KW(pn, "PN");
	FIND_VPD_KW(na, "NA");
#undef FIND_VPD_KW

	memcpy(p->id, vpd + PCI_VPD_LRDT_TAG_SIZE, id_len);
	strim(p->id);
	memcpy(p->ec, vpd + ec, EC_LEN);
	strim(p->ec);
	i = pci_vpd_info_field_size(vpd + sn - PCI_VPD_INFO_FLD_HDR_SIZE);
	memcpy(p->sn, vpd + sn, min(i, SERNUM_LEN));
	strim(p->sn);
	i = pci_vpd_info_field_size(vpd + pn - PCI_VPD_INFO_FLD_HDR_SIZE);
	memcpy(p->pn, vpd + pn, min(i, PN_LEN));
	strim(p->pn);
	memcpy(p->na, vpd + na, min(i, MACADDR_LEN));
	strim((char *)p->na);

out:
	vfree(vpd);
	return ret < 0 ? ret : 0;
}