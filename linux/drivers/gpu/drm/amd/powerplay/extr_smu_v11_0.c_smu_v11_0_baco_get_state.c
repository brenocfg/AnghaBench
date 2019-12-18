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
struct smu_baco_context {int state; int /*<<< orphan*/  mutex; } ;
struct smu_context {struct smu_baco_context smu_baco; } ;
typedef  enum smu_baco_state { ____Placeholder_smu_baco_state } smu_baco_state ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum smu_baco_state smu_v11_0_baco_get_state(struct smu_context *smu)
{
	struct smu_baco_context *smu_baco = &smu->smu_baco;
	enum smu_baco_state baco_state;

	mutex_lock(&smu_baco->mutex);
	baco_state = smu_baco->state;
	mutex_unlock(&smu_baco->mutex);

	return baco_state;
}