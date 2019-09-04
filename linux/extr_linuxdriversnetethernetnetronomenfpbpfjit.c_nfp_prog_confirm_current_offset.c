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
struct nfp_prog {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned int nfp_prog_current_offset (struct nfp_prog*) ; 

__attribute__((used)) static bool
nfp_prog_confirm_current_offset(struct nfp_prog *nfp_prog, unsigned int off)
{
	/* If there is a recorded error we may have dropped instructions;
	 * that doesn't have to be due to translator bug, and the translation
	 * will fail anyway, so just return OK.
	 */
	if (nfp_prog->error)
		return true;
	return !WARN_ON_ONCE(nfp_prog_current_offset(nfp_prog) != off);
}