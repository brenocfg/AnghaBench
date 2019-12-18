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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PKEY_SIZE_AES_192 ; 
 int /*<<< orphan*/  pkey_ccacipher_aes_attr_read (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t ccacipher_aes_192_read(struct file *filp,
				      struct kobject *kobj,
				      struct bin_attribute *attr,
				      char *buf, loff_t off,
				      size_t count)
{
	return pkey_ccacipher_aes_attr_read(PKEY_SIZE_AES_192, false, buf,
					    off, count);
}