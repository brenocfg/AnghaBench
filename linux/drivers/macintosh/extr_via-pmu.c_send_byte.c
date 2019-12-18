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

/* Variables and functions */
 size_t ACR ; 
 size_t B ; 
 size_t SR ; 
 int SR_EXT ; 
 int SR_OUT ; 
 int TREQ ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * via1 ; 
 int /*<<< orphan*/ * via2 ; 

__attribute__((used)) static inline void
send_byte(int x)
{
	out_8(&via1[ACR], in_8(&via1[ACR]) | SR_OUT | SR_EXT);
	out_8(&via1[SR], x);
	out_8(&via2[B], in_8(&via2[B]) & ~TREQ);	/* assert TREQ */
	(void)in_8(&via2[B]);
}