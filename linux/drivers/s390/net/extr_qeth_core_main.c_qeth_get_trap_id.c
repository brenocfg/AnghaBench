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
struct sysinfo_3_2_2 {TYPE_2__* vm; int /*<<< orphan*/  lpar_number; } ;
struct sysinfo_2_2_2 {TYPE_2__* vm; int /*<<< orphan*/  lpar_number; } ;
struct qeth_trap_id {int /*<<< orphan*/  vmname; int /*<<< orphan*/  lparnr; int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; int /*<<< orphan*/  chpid; } ;
struct TYPE_3__ {int /*<<< orphan*/  chpid; } ;
struct qeth_card {TYPE_1__ info; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  EBCASC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccw_device_get_id (int /*<<< orphan*/ ,struct ccw_dev_id*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stsi (struct sysinfo_3_2_2*,int,int,int) ; 

__attribute__((used)) static void qeth_get_trap_id(struct qeth_card *card, struct qeth_trap_id *tid)
{
	unsigned long info = get_zeroed_page(GFP_KERNEL);
	struct sysinfo_2_2_2 *info222 = (struct sysinfo_2_2_2 *)info;
	struct sysinfo_3_2_2 *info322 = (struct sysinfo_3_2_2 *)info;
	struct ccw_dev_id ccwid;
	int level;

	tid->chpid = card->info.chpid;
	ccw_device_get_id(CARD_RDEV(card), &ccwid);
	tid->ssid = ccwid.ssid;
	tid->devno = ccwid.devno;
	if (!info)
		return;
	level = stsi(NULL, 0, 0, 0);
	if ((level >= 2) && (stsi(info222, 2, 2, 2) == 0))
		tid->lparnr = info222->lpar_number;
	if ((level >= 3) && (stsi(info322, 3, 2, 2) == 0)) {
		EBCASC(info322->vm[0].name, sizeof(info322->vm[0].name));
		memcpy(tid->vmname, info322->vm[0].name, sizeof(tid->vmname));
	}
	free_page(info);
	return;
}