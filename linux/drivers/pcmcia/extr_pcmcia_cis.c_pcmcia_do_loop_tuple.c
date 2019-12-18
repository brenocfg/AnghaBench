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
typedef  int /*<<< orphan*/  tuple_t ;
struct pcmcia_loop_mem {int (* loop_tuple ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  priv_data; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  cisparse_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmcia_do_loop_tuple(tuple_t *tuple, cisparse_t *parse, void *priv)
{
	struct pcmcia_loop_mem *loop = priv;

	return loop->loop_tuple(loop->p_dev, tuple, loop->priv_data);
}