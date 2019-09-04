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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  MBCS_SRAM_SIZE ; 
 int /*<<< orphan*/  generic_file_llseek_size (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t mbcs_sram_llseek(struct file * filp, loff_t off, int whence)
{
	return generic_file_llseek_size(filp, off, whence, MAX_LFS_FILESIZE,
					MBCS_SRAM_SIZE);
}