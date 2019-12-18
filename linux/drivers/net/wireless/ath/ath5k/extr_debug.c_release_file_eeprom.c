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
struct inode {int dummy; } ;
struct file {struct eeprom_private* private_data; } ;
struct eeprom_private {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct eeprom_private*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int release_file_eeprom(struct inode *inode, struct file *file)
{
	struct eeprom_private *ep = file->private_data;

	vfree(ep->buf);
	kfree(ep);

	return 0;
}