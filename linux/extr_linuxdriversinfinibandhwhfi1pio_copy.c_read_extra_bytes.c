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
struct TYPE_2__ {int /*<<< orphan*/ * val8; } ;
struct pio_buf {size_t carry_bytes; TYPE_1__ carry; } ;

/* Variables and functions */
 int /*<<< orphan*/  jcopy (int /*<<< orphan*/ *,void const*,unsigned int) ; 

__attribute__((used)) static inline void read_extra_bytes(struct pio_buf *pbuf,
				    const void *from, unsigned int nbytes)
{
	jcopy(&pbuf->carry.val8[pbuf->carry_bytes], from, nbytes);
	pbuf->carry_bytes += nbytes;
}