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
struct saa7146_standard {scalar_t__ id; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct hexium {scalar_t__ cur_std; } ;

/* Variables and functions */
 scalar_t__ V4L2_STD_NTSC ; 
 scalar_t__ V4L2_STD_PAL ; 
 scalar_t__ V4L2_STD_SECAM ; 
 int /*<<< orphan*/  hexium_ntsc ; 
 int /*<<< orphan*/  hexium_pal ; 
 int /*<<< orphan*/  hexium_secam ; 
 int /*<<< orphan*/  hexium_set_standard (struct hexium*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int std_callback(struct saa7146_dev *dev, struct saa7146_standard *std)
{
	struct hexium *hexium = (struct hexium *) dev->ext_priv;

	if (V4L2_STD_PAL == std->id) {
		hexium_set_standard(hexium, hexium_pal);
		hexium->cur_std = V4L2_STD_PAL;
		return 0;
	} else if (V4L2_STD_NTSC == std->id) {
		hexium_set_standard(hexium, hexium_ntsc);
		hexium->cur_std = V4L2_STD_NTSC;
		return 0;
	} else if (V4L2_STD_SECAM == std->id) {
		hexium_set_standard(hexium, hexium_secam);
		hexium->cur_std = V4L2_STD_SECAM;
		return 0;
	}

	return -1;
}