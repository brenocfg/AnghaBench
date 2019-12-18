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
struct clone {int /*<<< orphan*/  mode; } ;
typedef  enum clone_metadata_mode { ____Placeholder_clone_metadata_mode } clone_metadata_mode ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum clone_metadata_mode get_clone_mode(struct clone *clone)
{
	return READ_ONCE(clone->mode);
}