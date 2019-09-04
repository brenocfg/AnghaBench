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
struct atmel_aes_reqctx {int mode; } ;
struct atmel_aes_dev {int flags; } ;

/* Variables and functions */
 int AES_FLAGS_PERSISTENT ; 

__attribute__((used)) static inline void atmel_aes_set_mode(struct atmel_aes_dev *dd,
				      const struct atmel_aes_reqctx *rctx)
{
	/* Clear all but persistent flags and set request flags. */
	dd->flags = (dd->flags & AES_FLAGS_PERSISTENT) | rctx->mode;
}