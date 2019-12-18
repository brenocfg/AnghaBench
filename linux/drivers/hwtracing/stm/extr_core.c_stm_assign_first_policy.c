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
struct stp_policy_node {int dummy; } ;
struct stm_output {int dummy; } ;
struct stm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int stm_output_assign (struct stm_device*,unsigned int,struct stp_policy_node*,struct stm_output*) ; 
 struct stp_policy_node* stp_policy_node_lookup (struct stm_device*,char*) ; 
 int /*<<< orphan*/  stp_policy_node_put (struct stp_policy_node*) ; 

__attribute__((used)) static int
stm_assign_first_policy(struct stm_device *stm, struct stm_output *output,
			char **ids, unsigned int width)
{
	struct stp_policy_node *pn;
	int err, n;

	/*
	 * On success, stp_policy_node_lookup() will return holding the
	 * configfs subsystem mutex, which is then released in
	 * stp_policy_node_put(). This allows the pdrv->output_open() in
	 * stm_output_assign() to serialize against the attribute accessors.
	 */
	for (n = 0, pn = NULL; ids[n] && !pn; n++)
		pn = stp_policy_node_lookup(stm, ids[n]);

	if (!pn)
		return -EINVAL;

	err = stm_output_assign(stm, width, pn, output);

	stp_policy_node_put(pn);

	return err;
}