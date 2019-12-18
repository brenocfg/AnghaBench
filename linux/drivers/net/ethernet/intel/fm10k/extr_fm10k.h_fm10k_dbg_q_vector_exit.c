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
struct fm10k_q_vector {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void fm10k_dbg_q_vector_exit(struct fm10k_q_vector *q_vector) {}