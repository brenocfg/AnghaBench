#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {TYPE_2__ core; } ;
struct TYPE_6__ {int (* lldd_write_gpio ) (struct sas_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_RESP_FUNC_ACC ; 
 int /*<<< orphan*/  SMP_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  SMP_RESP_FUNC_UNK ; 
 int stub1 (struct sas_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_host_smp_write_gpio(struct sas_ha_struct *sas_ha, u8 *resp_data,
				   u8 reg_type, u8 reg_index, u8 reg_count,
				   u8 *req_data)
{
	struct sas_internal *i = to_sas_internal(sas_ha->core.shost->transportt);
	int written;

	if (i->dft->lldd_write_gpio == NULL) {
		resp_data[2] = SMP_RESP_FUNC_UNK;
		return 0;
	}

	written = i->dft->lldd_write_gpio(sas_ha, reg_type, reg_index,
					  reg_count, req_data);

	if (written < 0) {
		resp_data[2] = SMP_RESP_FUNC_FAILED;
		written = 0;
	} else
		resp_data[2] = SMP_RESP_FUNC_ACC;

	return written;
}