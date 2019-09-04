#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct talitos_ptr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;
struct talitos_edesc {TYPE_1__ desc; } ;
struct talitos_ctx {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  padded_hash ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_PAD ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  map_single_talitos_ptr (int /*<<< orphan*/ ,struct talitos_ptr*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_once (char*) ; 

__attribute__((used)) static void talitos_handle_buggy_hash(struct talitos_ctx *ctx,
			       struct talitos_edesc *edesc,
			       struct talitos_ptr *ptr)
{
	static u8 padded_hash[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	pr_err_once("Bug in SEC1, padding ourself\n");
	edesc->desc.hdr &= ~DESC_HDR_MODE0_MDEU_PAD;
	map_single_talitos_ptr(ctx->dev, ptr, sizeof(padded_hash),
			       (char *)padded_hash, DMA_TO_DEVICE);
}