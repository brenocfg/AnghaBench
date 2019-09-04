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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  int u8 ;
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO2 ; 
#define  V4L2_STD_NTSC 131 
#define  V4L2_STD_PAL 130 
#define  V4L2_STD_SECAM 129 
#define  V4L2_STD_UNKNOWN 128 
 int saa_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static v4l2_std_id saa7134_read_std(struct saa7134_dev *dev)
{
	static v4l2_std_id stds[] = {
		V4L2_STD_UNKNOWN,
		V4L2_STD_NTSC,
		V4L2_STD_PAL,
		V4L2_STD_SECAM };

	v4l2_std_id result = 0;

	u8 st1 = saa_readb(SAA7134_STATUS_VIDEO1);
	u8 st2 = saa_readb(SAA7134_STATUS_VIDEO2);

	if (!(st2 & 0x1)) /* RDCAP == 0 */
		result = V4L2_STD_UNKNOWN;
	else
		result = stds[st1 & 0x03];

	return result;
}