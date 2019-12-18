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
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_nop (struct nfp_prog*) ; 

__attribute__((used)) static void wrp_nops(struct nfp_prog *nfp_prog, unsigned int count)
{
	while (count--)
		emit_nop(nfp_prog);
}