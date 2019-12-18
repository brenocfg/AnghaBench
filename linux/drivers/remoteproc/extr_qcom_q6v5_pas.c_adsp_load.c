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
struct rproc {int /*<<< orphan*/  firmware; scalar_t__ priv; } ;
struct qcom_adsp {int /*<<< orphan*/  mem_reloc; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_phys; int /*<<< orphan*/  mem_region; int /*<<< orphan*/  pas_id; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int qcom_mdt_load (int /*<<< orphan*/ ,struct firmware const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adsp_load(struct rproc *rproc, const struct firmware *fw)
{
	struct qcom_adsp *adsp = (struct qcom_adsp *)rproc->priv;

	return qcom_mdt_load(adsp->dev, fw, rproc->firmware, adsp->pas_id,
			     adsp->mem_region, adsp->mem_phys, adsp->mem_size,
			     &adsp->mem_reloc);

}