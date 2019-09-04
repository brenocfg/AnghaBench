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
struct jpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCCMD ; 
 int /*<<< orphan*/  JCCMD_SRST ; 
 int jpu_wait_reset (struct jpu*) ; 
 int /*<<< orphan*/  jpu_write (struct jpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpu_reset(struct jpu *jpu)
{
	jpu_write(jpu, JCCMD_SRST, JCCMD);
	return jpu_wait_reset(jpu);
}