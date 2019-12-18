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
typedef  int u32 ;
struct tg3 {int /*<<< orphan*/ * fw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_NVM_HWSB_CFG1 ; 
 int TG3_NVM_HWSB_CFG1_MAJMSK ; 
 int TG3_NVM_HWSB_CFG1_MAJSFT ; 
 int TG3_NVM_HWSB_CFG1_MINMSK ; 
 int TG3_NVM_HWSB_CFG1_MINSFT ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int,int) ; 
 scalar_t__ tg3_nvram_read (struct tg3*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void tg3_read_hwsb_ver(struct tg3 *tp)
{
	u32 val, major, minor;

	/* Use native endian representation */
	if (tg3_nvram_read(tp, TG3_NVM_HWSB_CFG1, &val))
		return;

	major = (val & TG3_NVM_HWSB_CFG1_MAJMSK) >>
		TG3_NVM_HWSB_CFG1_MAJSFT;
	minor = (val & TG3_NVM_HWSB_CFG1_MINMSK) >>
		TG3_NVM_HWSB_CFG1_MINSFT;

	snprintf(&tp->fw_ver[0], 32, "sb v%d.%02d", major, minor);
}