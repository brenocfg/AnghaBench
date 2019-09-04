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
struct pd_unit {scalar_t__ drive; int can_lba; int sectors; int heads; int cylinders; int capacity; int removable; int /*<<< orphan*/  standby; int /*<<< orphan*/  name; int /*<<< orphan*/  pi; } ;
typedef  enum action { ____Placeholder_action } action ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DBMSG (char*) ; 
 int /*<<< orphan*/  DRIVE (struct pd_unit*) ; 
 int Fail ; 
 int /*<<< orphan*/  IDE_IDENTIFY ; 
 int Ok ; 
 int PD_ID_LEN ; 
 int PD_ID_OFF ; 
 int /*<<< orphan*/  STAT_DRQ ; 
 int STAT_ERR ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_init_dev_parms (struct pd_unit*) ; 
 int /*<<< orphan*/  pd_reset (struct pd_unit*) ; 
 int* pd_scratch ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_standby_off (struct pd_unit*) ; 
 int pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_read_block (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,char*) ; 
 int /*<<< orphan*/  write_reg (struct pd_unit*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action pd_identify(struct pd_unit *disk)
{
	int j;
	char id[PD_ID_LEN + 1];

/* WARNING:  here there may be dragons.  reset() applies to both drives,
   but we call it only on probing the MASTER. This should allow most
   common configurations to work, but be warned that a reset can clear
   settings on the SLAVE drive.
*/

	if (disk->drive == 0)
		pd_reset(disk);

	write_reg(disk, 6, DRIVE(disk));
	pd_wait_for(disk, 0, DBMSG("before IDENT"));
	pd_send_command(disk, 1, 0, 0, 0, 0, IDE_IDENTIFY);

	if (pd_wait_for(disk, STAT_DRQ, DBMSG("IDENT DRQ")) & STAT_ERR)
		return Fail;
	pi_read_block(disk->pi, pd_scratch, 512);
	disk->can_lba = pd_scratch[99] & 2;
	disk->sectors = le16_to_cpu(*(__le16 *) (pd_scratch + 12));
	disk->heads = le16_to_cpu(*(__le16 *) (pd_scratch + 6));
	disk->cylinders = le16_to_cpu(*(__le16 *) (pd_scratch + 2));
	if (disk->can_lba)
		disk->capacity = le32_to_cpu(*(__le32 *) (pd_scratch + 120));
	else
		disk->capacity = disk->sectors * disk->heads * disk->cylinders;

	for (j = 0; j < PD_ID_LEN; j++)
		id[j ^ 1] = pd_scratch[j + PD_ID_OFF];
	j = PD_ID_LEN - 1;
	while ((j >= 0) && (id[j] <= 0x20))
		j--;
	j++;
	id[j] = 0;

	disk->removable = pd_scratch[0] & 0x80;

	printk("%s: %s, %s, %d blocks [%dM], (%d/%d/%d), %s media\n",
	       disk->name, id,
	       disk->drive ? "slave" : "master",
	       disk->capacity, disk->capacity / 2048,
	       disk->cylinders, disk->heads, disk->sectors,
	       disk->removable ? "removable" : "fixed");

	if (disk->capacity)
		pd_init_dev_parms(disk);
	if (!disk->standby)
		pd_standby_off(disk);

	return Ok;
}