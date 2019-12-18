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
typedef  int /*<<< orphan*/  u16 ;
struct rio_channel {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHOP ; 
 scalar_t__ IS_ERR (struct rio_channel*) ; 
 int /*<<< orphan*/  PTR_ERR (struct rio_channel*) ; 
 struct rio_channel* riocm_ch_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rio_channel *riocm_ch_create(u16 *ch_num)
{
	struct rio_channel *ch = NULL;

	ch = riocm_ch_alloc(*ch_num);

	if (IS_ERR(ch))
		riocm_debug(CHOP, "Failed to allocate channel %d (err=%ld)",
			    *ch_num, PTR_ERR(ch));
	else
		*ch_num = ch->id;

	return ch;
}