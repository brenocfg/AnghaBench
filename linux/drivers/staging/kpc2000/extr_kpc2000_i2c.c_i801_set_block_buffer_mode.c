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
struct i2c_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SMBAUXCTL (struct i2c_device*) ; 
 int SMBAUXCTL_E32B ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i801_set_block_buffer_mode(struct i2c_device *priv)
{
	outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_E32B, SMBAUXCTL(priv));
	if ((inb_p(SMBAUXCTL(priv)) & SMBAUXCTL_E32B) == 0)
		return -EIO;
	return 0;
}