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
struct hfi1_pportdata {int /*<<< orphan*/  port_xmit_discards; } ;

/* Variables and functions */
 int /*<<< orphan*/  incr_cntr64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __count_port_discards(struct hfi1_pportdata *ppd)
{
	incr_cntr64(&ppd->port_xmit_discards);
}