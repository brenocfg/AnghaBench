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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct img_hash_dev {int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DIV_ROUND_UP (size_t,int) ; 
 int /*<<< orphan*/  DRIVER_FLAGS_FINAL ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  writel_relaxed (size_t const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_hash_xmit_cpu(struct img_hash_dev *hdev, const u8 *buf,
			     size_t length, int final)
{
	u32 count, len32;
	const u32 *buffer = (const u32 *)buf;

	dev_dbg(hdev->dev, "xmit_cpu:  length: %zu bytes\n", length);

	if (final)
		hdev->flags |= DRIVER_FLAGS_FINAL;

	len32 = DIV_ROUND_UP(length, sizeof(u32));

	for (count = 0; count < len32; count++)
		writel_relaxed(buffer[count], hdev->cpu_addr);

	return -EINPROGRESS;
}