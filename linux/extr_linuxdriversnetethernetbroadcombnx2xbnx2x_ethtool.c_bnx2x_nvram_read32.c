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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int bnx2x_nvram_read (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bnx2x_nvram_read32(struct bnx2x *bp, u32 offset, u32 *buf,
			      int buf_size)
{
	int rc;

	rc = bnx2x_nvram_read(bp, offset, (u8 *)buf, buf_size);

	if (!rc) {
		__be32 *be = (__be32 *)buf;

		while ((buf_size -= 4) >= 0)
			*buf++ = be32_to_cpu(*be++);
	}

	return rc;
}