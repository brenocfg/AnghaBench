#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int /*<<< orphan*/  be64_add_cpu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void inc(be128 *iv)
{
	be64_add_cpu(&iv->b, 1);
	if (!iv->b)
		be64_add_cpu(&iv->a, 1);
}