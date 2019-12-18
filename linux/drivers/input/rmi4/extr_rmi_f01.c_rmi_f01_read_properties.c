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
typedef  int u8 ;
typedef  int u16 ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct f01_basic_properties {int manufacturer_id; int has_lts; int has_adjustable_doze; int has_adjustable_doze_holdoff; char* product_id; int productinfo; int firmware_id; int /*<<< orphan*/  package_id; int /*<<< orphan*/  dom; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int BIT (int) ; 
 int RMI_F01_BASIC_QUERY_LEN ; 
 int RMI_F01_QRY1_HAS_ADJ_DOZE ; 
 int RMI_F01_QRY1_HAS_ADJ_DOZE_HOFF ; 
 int RMI_F01_QRY1_HAS_LTS ; 
 int RMI_F01_QRY1_HAS_QUERY42 ; 
 int RMI_F01_QRY1_HAS_SENSOR_ID ; 
 int RMI_F01_QRY2_PRODINFO_MASK ; 
 int RMI_F01_QRY5_YEAR_MASK ; 
 int RMI_F01_QRY6_MONTH_MASK ; 
 int RMI_F01_QRY7_DAY_MASK ; 
 size_t RMI_PRODUCT_ID_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_unaligned_le64 (int*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,size_t) ; 
 int rmi_read (struct rmi_device*,int,int*) ; 
 int rmi_read_block (struct rmi_device*,int,int*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 

__attribute__((used)) static int rmi_f01_read_properties(struct rmi_device *rmi_dev,
				   u16 query_base_addr,
				   struct f01_basic_properties *props)
{
	u8 queries[RMI_F01_BASIC_QUERY_LEN];
	int ret;
	int query_offset = query_base_addr;
	bool has_ds4_queries = false;
	bool has_query42 = false;
	bool has_sensor_id = false;
	bool has_package_id_query = false;
	bool has_build_id_query = false;
	u16 prod_info_addr;
	u8 ds4_query_len;

	ret = rmi_read_block(rmi_dev, query_offset,
			       queries, RMI_F01_BASIC_QUERY_LEN);
	if (ret) {
		dev_err(&rmi_dev->dev,
			"Failed to read device query registers: %d\n", ret);
		return ret;
	}

	prod_info_addr = query_offset + 17;
	query_offset += RMI_F01_BASIC_QUERY_LEN;

	/* Now parse what we got */
	props->manufacturer_id = queries[0];

	props->has_lts = queries[1] & RMI_F01_QRY1_HAS_LTS;
	props->has_adjustable_doze =
			queries[1] & RMI_F01_QRY1_HAS_ADJ_DOZE;
	props->has_adjustable_doze_holdoff =
			queries[1] & RMI_F01_QRY1_HAS_ADJ_DOZE_HOFF;
	has_query42 = queries[1] & RMI_F01_QRY1_HAS_QUERY42;
	has_sensor_id = queries[1] & RMI_F01_QRY1_HAS_SENSOR_ID;

	snprintf(props->dom, sizeof(props->dom), "20%02d/%02d/%02d",
		 queries[5] & RMI_F01_QRY5_YEAR_MASK,
		 queries[6] & RMI_F01_QRY6_MONTH_MASK,
		 queries[7] & RMI_F01_QRY7_DAY_MASK);

	memcpy(props->product_id, &queries[11],
		RMI_PRODUCT_ID_LENGTH);
	props->product_id[RMI_PRODUCT_ID_LENGTH] = '\0';

	props->productinfo =
			((queries[2] & RMI_F01_QRY2_PRODINFO_MASK) << 7) |
			(queries[3] & RMI_F01_QRY2_PRODINFO_MASK);

	if (has_sensor_id)
		query_offset++;

	if (has_query42) {
		ret = rmi_read(rmi_dev, query_offset, queries);
		if (ret) {
			dev_err(&rmi_dev->dev,
				"Failed to read query 42 register: %d\n", ret);
			return ret;
		}

		has_ds4_queries = !!(queries[0] & BIT(0));
		query_offset++;
	}

	if (has_ds4_queries) {
		ret = rmi_read(rmi_dev, query_offset, &ds4_query_len);
		if (ret) {
			dev_err(&rmi_dev->dev,
				"Failed to read DS4 queries length: %d\n", ret);
			return ret;
		}
		query_offset++;

		if (ds4_query_len > 0) {
			ret = rmi_read(rmi_dev, query_offset, queries);
			if (ret) {
				dev_err(&rmi_dev->dev,
					"Failed to read DS4 queries: %d\n",
					ret);
				return ret;
			}

			has_package_id_query = !!(queries[0] & BIT(0));
			has_build_id_query = !!(queries[0] & BIT(1));
		}

		if (has_package_id_query) {
			ret = rmi_read_block(rmi_dev, prod_info_addr,
					     queries, sizeof(__le64));
			if (ret) {
				dev_err(&rmi_dev->dev,
					"Failed to read package info: %d\n",
					ret);
				return ret;
			}

			props->package_id = get_unaligned_le64(queries);
			prod_info_addr++;
		}

		if (has_build_id_query) {
			ret = rmi_read_block(rmi_dev, prod_info_addr, queries,
					    3);
			if (ret) {
				dev_err(&rmi_dev->dev,
					"Failed to read product info: %d\n",
					ret);
				return ret;
			}

			props->firmware_id = queries[1] << 8 | queries[0];
			props->firmware_id += queries[2] * 65536;
		}
	}

	return 0;
}