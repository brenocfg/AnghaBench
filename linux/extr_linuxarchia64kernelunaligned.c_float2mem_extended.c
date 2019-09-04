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
struct ia64_fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_ldf_fill (int,struct ia64_fpreg*) ; 
 int /*<<< orphan*/  ia64_stfe (struct ia64_fpreg*,int) ; 
 int /*<<< orphan*/  ia64_stop () ; 

__attribute__((used)) static inline void
float2mem_extended (struct ia64_fpreg *init, struct ia64_fpreg *final)
{
	ia64_ldf_fill(6, init);
	ia64_stop();
	ia64_stfe(final, 6);
}