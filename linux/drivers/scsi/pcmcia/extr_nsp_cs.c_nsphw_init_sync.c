#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  SyncOffset; int /*<<< orphan*/  SyncPeriod; int /*<<< orphan*/  SyncNegotiation; } ;
typedef  TYPE_1__ sync_data ;
struct TYPE_6__ {TYPE_1__* Sync; } ;
typedef  TYPE_2__ nsp_hw_data ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SYNC_NOT_YET ; 

__attribute__((used)) static void nsphw_init_sync(nsp_hw_data *data)
{
	sync_data tmp_sync = { .SyncNegotiation = SYNC_NOT_YET,
			       .SyncPeriod      = 0,
			       .SyncOffset      = 0
	};
	int i;

	/* setup sync data */
	for ( i = 0; i < ARRAY_SIZE(data->Sync); i++ ) {
		data->Sync[i] = tmp_sync;
	}
}