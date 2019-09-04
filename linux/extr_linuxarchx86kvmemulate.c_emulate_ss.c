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
struct x86_emulate_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_VECTOR ; 
 int emulate_exception (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int emulate_ss(struct x86_emulate_ctxt *ctxt, int err)
{
	return emulate_exception(ctxt, SS_VECTOR, err, true);
}