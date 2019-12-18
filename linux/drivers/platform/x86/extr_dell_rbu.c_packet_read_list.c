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
struct list_head {struct list_head* next; } ;
struct TYPE_4__ {struct list_head* next; } ;
struct TYPE_6__ {TYPE_1__ list; } ;
struct TYPE_5__ {scalar_t__ num_packets; int packet_read_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int do_packet_read (char*,struct list_head*,int,int,int*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 TYPE_3__ packet_data_head ; 
 TYPE_2__ rbu_data ; 

__attribute__((used)) static int packet_read_list(char *data, size_t * pread_length)
{
	struct list_head *ptemp_list;
	int temp_count = 0;
	int bytes_copied = 0;
	int bytes_read = 0;
	int remaining_bytes = 0;
	char *pdest = data;

	/* check if we have any packets */
	if (0 == rbu_data.num_packets)
		return -ENOMEM;

	remaining_bytes = *pread_length;
	bytes_read = rbu_data.packet_read_count;

	ptemp_list = (&packet_data_head.list)->next;
	while (!list_empty(ptemp_list)) {
		bytes_copied = do_packet_read(pdest, ptemp_list,
			remaining_bytes, bytes_read, &temp_count);
		remaining_bytes -= bytes_copied;
		bytes_read += bytes_copied;
		pdest += bytes_copied;
		/*
		 * check if we reached end of buffer before reaching the
		 * last packet
		 */
		if (remaining_bytes == 0)
			break;

		ptemp_list = ptemp_list->next;
	}
	/*finally set the bytes read */
	*pread_length = bytes_read - rbu_data.packet_read_count;
	rbu_data.packet_read_count = bytes_read;
	return 0;
}