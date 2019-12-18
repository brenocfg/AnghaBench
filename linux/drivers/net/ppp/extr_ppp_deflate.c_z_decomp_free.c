#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  workspace; } ;
struct ppp_deflate_state {TYPE_1__ strm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ppp_deflate_state*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflateEnd (TYPE_1__*) ; 

__attribute__((used)) static void z_decomp_free(void *arg)
{
	struct ppp_deflate_state *state = (struct ppp_deflate_state *) arg;

	if (state) {
		zlib_inflateEnd(&state->strm);
		vfree(state->strm.workspace);
		kfree(state);
	}
}