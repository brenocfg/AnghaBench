#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  buf_size; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct TYPE_6__ {TYPE_2__ buf; } ;
struct ksz_desc {TYPE_3__ sw; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_tx_len(struct ksz_desc *desc, u32 len)
{
	desc->sw.buf.tx.buf_size = len;
}