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
struct poly1305_desc_ctx {void** s; } ;

/* Variables and functions */
 void* get_unaligned_le32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void poly1305_setskey(struct poly1305_desc_ctx *dctx, const u8 *key)
{
	dctx->s[0] = get_unaligned_le32(key +  0);
	dctx->s[1] = get_unaligned_le32(key +  4);
	dctx->s[2] = get_unaligned_le32(key +  8);
	dctx->s[3] = get_unaligned_le32(key + 12);
}