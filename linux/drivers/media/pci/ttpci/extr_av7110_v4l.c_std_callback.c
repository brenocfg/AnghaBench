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
struct saa7146_standard {int id; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct av7110 {int /*<<< orphan*/  vidmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV7110_VIDEO_MODE_NTSC ; 
 int /*<<< orphan*/  AV7110_VIDEO_MODE_PAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int /*<<< orphan*/  av7110_set_vidmode (struct av7110*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int std_callback(struct saa7146_dev* dev, struct saa7146_standard *std)
{
	struct av7110 *av7110 = (struct av7110*) dev->ext_priv;

	if (std->id & V4L2_STD_PAL) {
		av7110->vidmode = AV7110_VIDEO_MODE_PAL;
		av7110_set_vidmode(av7110, av7110->vidmode);
	}
	else if (std->id & V4L2_STD_NTSC) {
		av7110->vidmode = AV7110_VIDEO_MODE_NTSC;
		av7110_set_vidmode(av7110, av7110->vidmode);
	}
	else
		return -1;

	return 0;
}