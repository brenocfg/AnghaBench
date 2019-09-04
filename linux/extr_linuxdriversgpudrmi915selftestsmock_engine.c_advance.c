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
struct TYPE_2__ {int /*<<< orphan*/  global_seqno; } ;
struct mock_request {TYPE_1__ base; int /*<<< orphan*/  link; } ;
struct mock_engine {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mock_seqno_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void advance(struct mock_engine *engine,
		    struct mock_request *request)
{
	list_del_init(&request->link);
	mock_seqno_advance(&engine->base, request->base.global_seqno);
}