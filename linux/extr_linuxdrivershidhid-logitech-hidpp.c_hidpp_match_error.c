#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ feature_index; scalar_t__ funcindex_clientid; scalar_t__* params; } ;
struct TYPE_3__ {scalar_t__ sub_id; } ;
struct hidpp_report {TYPE_2__ fap; TYPE_1__ rap; } ;

/* Variables and functions */
 scalar_t__ HIDPP20_ERROR ; 
 scalar_t__ HIDPP_ERROR ; 

__attribute__((used)) static inline bool hidpp_match_error(struct hidpp_report *question,
		struct hidpp_report *answer)
{
	return ((answer->rap.sub_id == HIDPP_ERROR) ||
	    (answer->fap.feature_index == HIDPP20_ERROR)) &&
	    (answer->fap.funcindex_clientid == question->fap.feature_index) &&
	    (answer->fap.params[0] == question->fap.funcindex_clientid);
}