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
struct mtk_aes_reqctx {int mode; } ;
struct mtk_aes_rec {int flags; } ;

/* Variables and functions */
 int AES_FLAGS_BUSY ; 

__attribute__((used)) static inline void mtk_aes_set_mode(struct mtk_aes_rec *aes,
				    const struct mtk_aes_reqctx *rctx)
{
	/* Clear all but persistent flags and set request flags. */
	aes->flags = (aes->flags & AES_FLAGS_BUSY) | rctx->mode;
}