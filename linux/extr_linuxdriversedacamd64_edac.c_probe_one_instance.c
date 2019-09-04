#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct ecc_settings {int dummy; } ;
struct TYPE_4__ {int x86; } ;
struct TYPE_3__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amd64_err (char*,unsigned int) ; 
 int /*<<< orphan*/  amd64_warn (char*) ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  ecc_enable_override ; 
 int /*<<< orphan*/  ecc_enabled (struct pci_dev*,unsigned int) ; 
 struct ecc_settings** ecc_stngs ; 
 int /*<<< orphan*/  enable_ecc_error_reporting (struct ecc_settings*,unsigned int,struct pci_dev*) ; 
 int init_one_instance (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ecc_settings*) ; 
 struct ecc_settings* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* node_to_amd_nb (unsigned int) ; 
 int /*<<< orphan*/  restore_ecc_error_reporting (struct ecc_settings*,unsigned int,struct pci_dev*) ; 

__attribute__((used)) static int probe_one_instance(unsigned int nid)
{
	struct pci_dev *F3 = node_to_amd_nb(nid)->misc;
	struct ecc_settings *s;
	int ret;

	ret = -ENOMEM;
	s = kzalloc(sizeof(struct ecc_settings), GFP_KERNEL);
	if (!s)
		goto err_out;

	ecc_stngs[nid] = s;

	if (!ecc_enabled(F3, nid)) {
		ret = 0;

		if (!ecc_enable_override)
			goto err_enable;

		if (boot_cpu_data.x86 >= 0x17) {
			amd64_warn("Forcing ECC on is not recommended on newer systems. Please enable ECC in BIOS.");
			goto err_enable;
		} else
			amd64_warn("Forcing ECC on!\n");

		if (!enable_ecc_error_reporting(s, nid, F3))
			goto err_enable;
	}

	ret = init_one_instance(nid);
	if (ret < 0) {
		amd64_err("Error probing instance: %d\n", nid);

		if (boot_cpu_data.x86 < 0x17)
			restore_ecc_error_reporting(s, nid, F3);

		goto err_enable;
	}

	return ret;

err_enable:
	kfree(s);
	ecc_stngs[nid] = NULL;

err_out:
	return ret;
}