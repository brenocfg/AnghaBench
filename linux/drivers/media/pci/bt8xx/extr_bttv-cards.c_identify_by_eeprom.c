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
struct TYPE_3__ {int type; int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BTTV_BOARD_EURESYS_PICOLO ; 
 int BTTV_BOARD_HAUPPAUGE ; 
 int BTTV_BOARD_MODTEC_205 ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

__attribute__((used)) static void identify_by_eeprom(struct bttv *btv, unsigned char eeprom_data[256])
{
	int type = -1;

	if (0 == strncmp(eeprom_data,"GET MM20xPCTV",13))
		type = BTTV_BOARD_MODTEC_205;
	else if (0 == strncmp(eeprom_data+20,"Picolo",7))
		type = BTTV_BOARD_EURESYS_PICOLO;
	else if (eeprom_data[0] == 0x84 && eeprom_data[2]== 0)
		type = BTTV_BOARD_HAUPPAUGE; /* old bt848 */

	if (-1 != type) {
		btv->c.type = type;
		pr_info("%d: detected by eeprom: %s [card=%d]\n",
			btv->c.nr, bttv_tvcards[btv->c.type].name, btv->c.type);
	}
}