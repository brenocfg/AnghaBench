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
struct dm_verity_fec {int dummy; } ;
struct dm_verity {struct dm_verity_fec* fec; TYPE_1__* ti; } ;
struct TYPE_2__ {char* error; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dm_verity_fec* kzalloc (int,int /*<<< orphan*/ ) ; 

int verity_fec_ctr_alloc(struct dm_verity *v)
{
	struct dm_verity_fec *f;

	f = kzalloc(sizeof(struct dm_verity_fec), GFP_KERNEL);
	if (!f) {
		v->ti->error = "Cannot allocate FEC structure";
		return -ENOMEM;
	}
	v->fec = f;

	return 0;
}