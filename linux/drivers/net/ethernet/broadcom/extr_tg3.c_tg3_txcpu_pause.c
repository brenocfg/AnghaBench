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
 int /*<<< orphan*/  TX_CPU_BASE ; 
 int tg3_pause_cpu (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_txcpu_pause(struct tg3 *tp)
{
	return tg3_pause_cpu(tp, TX_CPU_BASE);
}