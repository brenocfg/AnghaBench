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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int ANT_PATH_INTERNAL ; 
 int mxl111sf_idac_config (struct mxl111sf_state*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mxl111sf_set_ant_path(struct mxl111sf_state *state,
					int antpath)
{
	return mxl111sf_idac_config(state, 1, 1,
				    (antpath == ANT_PATH_INTERNAL) ?
				    0x3f : 0x00, 0);
}