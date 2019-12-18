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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CPU_BASE ; 
 int /*<<< orphan*/  tg3_resume_cpu (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_rxcpu_resume(struct tg3 *tp)
{
	tg3_resume_cpu(tp, RX_CPU_BASE);
}