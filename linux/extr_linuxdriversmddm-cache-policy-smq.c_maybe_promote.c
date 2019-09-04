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
typedef  enum promote_result { ____Placeholder_promote_result } promote_result ;

/* Variables and functions */
 int PROMOTE_NOT ; 
 int PROMOTE_PERMANENT ; 

__attribute__((used)) static enum promote_result maybe_promote(bool promote)
{
	return promote ? PROMOTE_PERMANENT : PROMOTE_NOT;
}