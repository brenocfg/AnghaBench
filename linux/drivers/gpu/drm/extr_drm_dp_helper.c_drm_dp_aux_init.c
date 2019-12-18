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
struct TYPE_4__ {int retries; int /*<<< orphan*/ * lock_ops; struct drm_dp_aux* algo_data; int /*<<< orphan*/ * algo; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct drm_dp_aux {TYPE_2__ ddc; int /*<<< orphan*/  crc_work; TYPE_1__ cec; int /*<<< orphan*/  hw_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_aux_crc_work ; 
 int /*<<< orphan*/  drm_dp_i2c_algo ; 
 int /*<<< orphan*/  drm_dp_i2c_lock_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void drm_dp_aux_init(struct drm_dp_aux *aux)
{
	mutex_init(&aux->hw_mutex);
	mutex_init(&aux->cec.lock);
	INIT_WORK(&aux->crc_work, drm_dp_aux_crc_work);

	aux->ddc.algo = &drm_dp_i2c_algo;
	aux->ddc.algo_data = aux;
	aux->ddc.retries = 3;

	aux->ddc.lock_ops = &drm_dp_i2c_lock_ops;
}