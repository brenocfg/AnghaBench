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
struct au0828_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_000 ; 
 int /*<<< orphan*/  au0828_clear (struct au0828_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  au0828_set (struct au0828_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hvr950q_cs5340_audio(void *priv, int enable)
{
	/* Because the HVR-950q shares an i2s bus between the cs5340 and the
	   au8522, we need to hold cs5340 in reset when using the au8522 */
	struct au0828_dev *dev = priv;
	if (enable == 1)
		au0828_set(dev, REG_000, 0x10);
	else
		au0828_clear(dev, REG_000, 0x10);
}