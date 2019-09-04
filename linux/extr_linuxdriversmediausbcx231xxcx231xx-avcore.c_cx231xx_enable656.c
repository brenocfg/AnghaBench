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
typedef  int u8 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS1_PIN_CTL0 ; 
 int /*<<< orphan*/  TS1_PIN_CTL1 ; 
 int /*<<< orphan*/  vid_blk_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vid_blk_write_byte (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

void cx231xx_enable656(struct cx231xx *dev)
{
	u8 temp = 0;
	/*enable TS1 data[0:7] as output to export 656*/

	vid_blk_write_byte(dev, TS1_PIN_CTL0, 0xFF);

	/*enable TS1 clock as output to export 656*/

	vid_blk_read_byte(dev, TS1_PIN_CTL1, &temp);
	temp = temp|0x04;

	vid_blk_write_byte(dev, TS1_PIN_CTL1, temp);
}