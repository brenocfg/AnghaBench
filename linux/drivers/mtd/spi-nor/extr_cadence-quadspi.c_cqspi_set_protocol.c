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
struct spi_nor {int read_proto; struct cqspi_flash_pdata* priv; } ;
struct cqspi_flash_pdata {void* data_width; void* addr_width; void* inst_width; } ;

/* Variables and functions */
 void* CQSPI_INST_TYPE_DUAL ; 
 void* CQSPI_INST_TYPE_OCTAL ; 
 void* CQSPI_INST_TYPE_QUAD ; 
 void* CQSPI_INST_TYPE_SINGLE ; 
 int EINVAL ; 
#define  SNOR_PROTO_1_1_1 131 
#define  SNOR_PROTO_1_1_2 130 
#define  SNOR_PROTO_1_1_4 129 
#define  SNOR_PROTO_1_1_8 128 
 int /*<<< orphan*/  cqspi_configure (struct spi_nor*) ; 

__attribute__((used)) static int cqspi_set_protocol(struct spi_nor *nor, const int read)
{
	struct cqspi_flash_pdata *f_pdata = nor->priv;

	f_pdata->inst_width = CQSPI_INST_TYPE_SINGLE;
	f_pdata->addr_width = CQSPI_INST_TYPE_SINGLE;
	f_pdata->data_width = CQSPI_INST_TYPE_SINGLE;

	if (read) {
		switch (nor->read_proto) {
		case SNOR_PROTO_1_1_1:
			f_pdata->data_width = CQSPI_INST_TYPE_SINGLE;
			break;
		case SNOR_PROTO_1_1_2:
			f_pdata->data_width = CQSPI_INST_TYPE_DUAL;
			break;
		case SNOR_PROTO_1_1_4:
			f_pdata->data_width = CQSPI_INST_TYPE_QUAD;
			break;
		case SNOR_PROTO_1_1_8:
			f_pdata->data_width = CQSPI_INST_TYPE_OCTAL;
			break;
		default:
			return -EINVAL;
		}
	}

	cqspi_configure(nor);

	return 0;
}