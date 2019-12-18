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
struct dm_buffer {int dummy; } ;
struct dm_block {int dummy; } ;
struct buffer_aux {TYPE_1__* validator; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prepare_for_write ) (TYPE_1__*,struct dm_block*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct buffer_aux* dm_bufio_get_aux_data (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_get_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bufio_get_client (struct dm_buffer*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct dm_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_block_manager_write_callback(struct dm_buffer *buf)
{
	struct buffer_aux *aux = dm_bufio_get_aux_data(buf);
	if (aux->validator) {
		aux->validator->prepare_for_write(aux->validator, (struct dm_block *) buf,
			 dm_bufio_get_block_size(dm_bufio_get_client(buf)));
	}
}