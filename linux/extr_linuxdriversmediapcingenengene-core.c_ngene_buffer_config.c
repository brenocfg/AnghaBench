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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ en; } ;
struct ngene {TYPE_2__* card_info; TYPE_1__ ci; } ;
struct TYPE_4__ {int fw_version; int* io_type; } ;

/* Variables and functions */
 int BUFFER_CONFIG_3333 ; 
 int BUFFER_CONFIG_4422 ; 
 int NGENE_IO_TSIN ; 
 int NGENE_IO_TSOUT ; 
 int ngene_command_config_buf (struct ngene*,int) ; 
 int ngene_command_config_free_buf (struct ngene*,int*) ; 

__attribute__((used)) static int ngene_buffer_config(struct ngene *dev)
{
	int stat;

	if (dev->card_info->fw_version >= 17) {
		u8 tsin12_config[6]   = { 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 };
		u8 tsin1234_config[6] = { 0x30, 0x30, 0x00, 0x30, 0x30, 0x00 };
		u8 tsio1235_config[6] = { 0x30, 0x30, 0x00, 0x28, 0x00, 0x38 };
		u8 *bconf = tsin12_config;

		if (dev->card_info->io_type[2]&NGENE_IO_TSIN &&
		    dev->card_info->io_type[3]&NGENE_IO_TSIN) {
			bconf = tsin1234_config;
			if (dev->card_info->io_type[4]&NGENE_IO_TSOUT &&
			    dev->ci.en)
				bconf = tsio1235_config;
		}
		stat = ngene_command_config_free_buf(dev, bconf);
	} else {
		int bconf = BUFFER_CONFIG_4422;

		if (dev->card_info->io_type[3] == NGENE_IO_TSIN)
			bconf = BUFFER_CONFIG_3333;
		stat = ngene_command_config_buf(dev, bconf);
	}
	return stat;
}