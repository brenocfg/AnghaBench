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
struct fs_dev {int dummy; } ;
struct freepool {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_CNF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_CTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_EA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_SA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_freepool(struct fs_dev *dev, struct freepool *fp)
{
	func_enter ();

	write_fs (dev, FP_CNF(fp->offset), 0);
	write_fs (dev, FP_SA (fp->offset), 0);
	write_fs (dev, FP_EA (fp->offset), 0);
	write_fs (dev, FP_CNT(fp->offset), 0);
	write_fs (dev, FP_CTU(fp->offset), 0);

	func_exit ();
}