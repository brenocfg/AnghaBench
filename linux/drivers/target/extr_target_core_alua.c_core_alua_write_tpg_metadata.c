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
typedef  int /*<<< orphan*/  u32 ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 struct file* filp_open (char const*,int,int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int kernel_write (struct file*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int core_alua_write_tpg_metadata(
	const char *path,
	unsigned char *md_buf,
	u32 md_buf_len)
{
	struct file *file = filp_open(path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	loff_t pos = 0;
	int ret;

	if (IS_ERR(file)) {
		pr_err("filp_open(%s) for ALUA metadata failed\n", path);
		return -ENODEV;
	}
	ret = kernel_write(file, md_buf, md_buf_len, &pos);
	if (ret < 0)
		pr_err("Error writing ALUA metadata file: %s\n", path);
	fput(file);
	return (ret < 0) ? -EIO : 0;
}