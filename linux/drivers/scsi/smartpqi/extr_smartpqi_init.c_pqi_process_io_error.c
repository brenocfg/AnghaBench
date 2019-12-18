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
struct pqi_io_request {int dummy; } ;

/* Variables and functions */
#define  PQI_RESPONSE_IU_AIO_PATH_IO_ERROR 129 
#define  PQI_RESPONSE_IU_RAID_PATH_IO_ERROR 128 
 int /*<<< orphan*/  pqi_process_aio_io_error (struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_process_raid_io_error (struct pqi_io_request*) ; 

__attribute__((used)) static void pqi_process_io_error(unsigned int iu_type,
	struct pqi_io_request *io_request)
{
	switch (iu_type) {
	case PQI_RESPONSE_IU_RAID_PATH_IO_ERROR:
		pqi_process_raid_io_error(io_request);
		break;
	case PQI_RESPONSE_IU_AIO_PATH_IO_ERROR:
		pqi_process_aio_io_error(io_request);
		break;
	}
}