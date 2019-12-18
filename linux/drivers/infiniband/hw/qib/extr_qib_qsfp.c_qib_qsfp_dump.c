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
typedef  int /*<<< orphan*/  u8 ;
struct qib_qsfp_cache {int tech; int len; int /*<<< orphan*/  lot; int /*<<< orphan*/  date; int /*<<< orphan*/  serial; int /*<<< orphan*/  atten; int /*<<< orphan*/  rev; int /*<<< orphan*/  partnum; int /*<<< orphan*/  oui; int /*<<< orphan*/  vendor; int /*<<< orphan*/  pwr; } ;
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSFP_ATTEN_DDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSFP_ATTEN_SDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSFP_DATE_LEN ; 
 int QSFP_DEFAULT_HDR_CNT ; 
 int QSFP_DUMP_CHUNK ; 
 scalar_t__ QSFP_IS_CU (int) ; 
 int /*<<< orphan*/  QSFP_LOT_LEN ; 
 int /*<<< orphan*/  QSFP_OUI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSFP_PN_LEN ; 
 int QSFP_PWR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSFP_REV_LEN ; 
 int /*<<< orphan*/  QSFP_SN_LEN ; 
 int /*<<< orphan*/  QSFP_VEND_LEN ; 
 scalar_t__ pwr_codes ; 
 int /*<<< orphan*/ * qib_qsfp_devtech ; 
 int qib_refresh_qsfp_cache (struct qib_pportdata*,struct qib_qsfp_cache*) ; 
 int qsfp_read (struct qib_pportdata*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ scnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int qib_qsfp_dump(struct qib_pportdata *ppd, char *buf, int len)
{
	struct qib_qsfp_cache cd;
	u8 bin_buff[QSFP_DUMP_CHUNK];
	char lenstr[6];
	int sofar, ret;
	int bidx = 0;

	sofar = 0;
	ret = qib_refresh_qsfp_cache(ppd, &cd);
	if (ret < 0)
		goto bail;

	lenstr[0] = ' ';
	lenstr[1] = '\0';
	if (QSFP_IS_CU(cd.tech))
		sprintf(lenstr, "%dM ", cd.len);

	sofar += scnprintf(buf + sofar, len - sofar, "PWR:%.3sW\n", pwr_codes +
			   (QSFP_PWR(cd.pwr) * 4));

	sofar += scnprintf(buf + sofar, len - sofar, "TECH:%s%s\n", lenstr,
			   qib_qsfp_devtech[cd.tech >> 4]);

	sofar += scnprintf(buf + sofar, len - sofar, "Vendor:%.*s\n",
			   QSFP_VEND_LEN, cd.vendor);

	sofar += scnprintf(buf + sofar, len - sofar, "OUI:%06X\n",
			   QSFP_OUI(cd.oui));

	sofar += scnprintf(buf + sofar, len - sofar, "Part#:%.*s\n",
			   QSFP_PN_LEN, cd.partnum);
	sofar += scnprintf(buf + sofar, len - sofar, "Rev:%.*s\n",
			   QSFP_REV_LEN, cd.rev);
	if (QSFP_IS_CU(cd.tech))
		sofar += scnprintf(buf + sofar, len - sofar, "Atten:%d, %d\n",
				   QSFP_ATTEN_SDR(cd.atten),
				   QSFP_ATTEN_DDR(cd.atten));
	sofar += scnprintf(buf + sofar, len - sofar, "Serial:%.*s\n",
			   QSFP_SN_LEN, cd.serial);
	sofar += scnprintf(buf + sofar, len - sofar, "Date:%.*s\n",
			   QSFP_DATE_LEN, cd.date);
	sofar += scnprintf(buf + sofar, len - sofar, "Lot:%.*s\n",
			   QSFP_LOT_LEN, cd.lot);

	while (bidx < QSFP_DEFAULT_HDR_CNT) {
		int iidx;

		ret = qsfp_read(ppd, bidx, bin_buff, QSFP_DUMP_CHUNK);
		if (ret < 0)
			goto bail;
		for (iidx = 0; iidx < ret; ++iidx) {
			sofar += scnprintf(buf + sofar, len-sofar, " %02X",
				bin_buff[iidx]);
		}
		sofar += scnprintf(buf + sofar, len - sofar, "\n");
		bidx += QSFP_DUMP_CHUNK;
	}
	ret = sofar;
bail:
	return ret;
}