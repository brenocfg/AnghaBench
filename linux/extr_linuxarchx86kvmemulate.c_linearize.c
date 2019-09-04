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
typedef  int /*<<< orphan*/  ulong ;
struct x86_emulate_ctxt {int /*<<< orphan*/  mode; } ;
struct segmented_address {int dummy; } ;

/* Variables and functions */
 int __linearize (struct x86_emulate_ctxt*,struct segmented_address,unsigned int*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int linearize(struct x86_emulate_ctxt *ctxt,
		     struct segmented_address addr,
		     unsigned size, bool write,
		     ulong *linear)
{
	unsigned max_size;
	return __linearize(ctxt, addr, &max_size, size, write, false,
			   ctxt->mode, linear);
}