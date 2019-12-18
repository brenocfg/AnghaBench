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
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
#define  SSPP_RGB0 131 
#define  SSPP_RGB1 130 
#define  SSPP_RGB2 129 
#define  SSPP_RGB3 128 

__attribute__((used)) static inline int pipe2nclients(enum mdp5_pipe pipe)
{
	switch (pipe) {
	case SSPP_RGB0:
	case SSPP_RGB1:
	case SSPP_RGB2:
	case SSPP_RGB3:
		return 1;
	default:
		return 3;
	}
}