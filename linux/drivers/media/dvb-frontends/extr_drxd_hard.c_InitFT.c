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
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_REG_COMM_EXEC__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int InitFT(struct drxd_state *state)
{
	/*
	   norm OFFSET,  MB says =2 voor 8K en =3 voor 2K waarschijnlijk
	   SC stuff
	 */
	return Write16(state, FT_REG_COMM_EXEC__A, 0x0001, 0x0000);
}