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
struct poly1305_desc_ctx {int* r; } ;

/* Variables and functions */
 int get_unaligned_le32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void poly1305_setrkey(struct poly1305_desc_ctx *dctx, const u8 *key)
{
	/* r &= 0xffffffc0ffffffc0ffffffc0fffffff */
	dctx->r[0] = (get_unaligned_le32(key +  0) >> 0) & 0x3ffffff;
	dctx->r[1] = (get_unaligned_le32(key +  3) >> 2) & 0x3ffff03;
	dctx->r[2] = (get_unaligned_le32(key +  6) >> 4) & 0x3ffc0ff;
	dctx->r[3] = (get_unaligned_le32(key +  9) >> 6) & 0x3f03fff;
	dctx->r[4] = (get_unaligned_le32(key + 12) >> 8) & 0x00fffff;
}